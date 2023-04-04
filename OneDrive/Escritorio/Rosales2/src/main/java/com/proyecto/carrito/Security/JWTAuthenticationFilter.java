package com.proyecto.carrito.Security;

import java.util.Collections;

import javax.naming.AuthenticationException;

import org.springframework.boot.autoconfigure.neo4j.Neo4jProperties.Authentication;
import org.springframework.security.web.authentication.UsernamePasswordAuthenticationFilter;

import com.fasterxml.jackson.databind.ObjectMapper;

import io.jsonwebtoken.io.IOException;
import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

public class JWTAuthenticationFilter extends UsernamePasswordAuthenticationFilter {

    
	@Override
	public Authentication attemptAuthentication(HttpServletRequest request,HttpServletResponse response)throws AuthenticationException{
	    
	
		AuthCredentials authCredentials= new AuthCredentials();
		
		
		try {
		
		authCredentials= new ObjectMapper().readValue(request.getReader(),AuthCredentials.class);
		}catch(IOException e) {
			
		}
		
		
		UsernamePasswordAuthenticationToken usernamePAT= new UsernamePasswordAuthenticationToken(
				authCredentials.getEmail(),
				authCredentials.getPassword(),
				Collections.emptyList()
				
				
				
				);
		
     return getAuthenticationManager().authenticate( usernamePAT);
	 
	}
	
	protected void successfulAuhentication(HttpServletRequest request,
			                               HttpServletResponse response,FilterChain chain,Authentication authResult) throws IOException,ServletException{
	      
		UserDetailsImpl userDetails=((Object) authResult).getPrincipal();
		String token= TokenUnits.createToken(userDetails.getNombre(),userDetails.getUsername());
		
		response.addHeader("Authorization", "Bearer" + token);
		response.getWriter().flush();
		
		super.successfulAuthentication(request, response, chain, (org.springframework.security.core.Authentication) authResult);
		
		
		
     }
	
}
	


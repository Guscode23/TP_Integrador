package com.proyecto.carrito.Security;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.provisioning.InMemoryUserDetailsManager;
import org.springframework.security.web.SecurityFilterChain;


@Configuration
public class WebSecurityConfig {

	
	private final UserDetailsService userDetailsService;
	private final JWTAuthoizationFilter jwtAuthorizationFilter;
	
	
	
	
	
	@SuppressWarnings("deprecation")
	@Bean
	SecurityFilterChain filterChain(HttpSecurity http, AuthenticationManager authManeger) throws Exception {
		
		JWTAuthenticationFilter jwtAuthFilter= new JWTAuthenticationFilter();
		jwtAuthFilter.setAuthenticationManager(authManeger);
		jwtAuthFilter.setFilterProcessesUrl("/login");
		
		return http
			.csrf().disable()
		    .authorizeRequests()
		    .anyRequest()
		    .authenticated()
		    .and()
		    .httpBasic()
		    .and()
		    .sessionManagement()
		    .sessionCreationPolicy(SessionCreationPolicy.STATELESS)
		    .and()
		    .addFilter(jwtAuthFilter)
		    .addFilterBefore(jwtAuthorizationFilter,UsernamePasswordAuthenticationFilter.class)
		    .build();
		    
	}
	
	/*@Bean
	  UserDetailsService userDetailsService() {
		InMemoryUserDetailsManager manager=new InMemoryUserDetailsManager();
		manager.createUser(User.withUsername("admin")
				.password("admin")
				.roles()
		        .build());
		return manager;
		
	}*/
	
	@Bean
	AuthenticationManager authManeger(HttpSecurity http)throws Exception {
		return http.getSharedObject(AuthenticationManagerBuilder.class)
				.userDetailsService(userDetailsService)
				.passwordEncoder(passwordEncoder())
				.and()
				.build();
	}
	
	
	@Bean
	PasswordEncoder passwordEncoder() {
		
		return new BCryptPasswordEncoder();
		
	}
	
	
	
	
}

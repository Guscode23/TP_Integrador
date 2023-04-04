package com.proyecto.carrito.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;

import com.proyecto.carrito.model.Cliente;
import com.proyecto.carrito.model.Transaccion;

public interface IOrdenRepository extends JpaRepository<Transaccion,Integer> {
	List<Transaccion> findByUsuario (Cliente usuario);
}
